// Parse Platform Plugin
// Created by Patryk Stepniewski
// Copyright © 2014-2016 gameDNA studio. All Rights Reserved.

package com.epicgames.ue4;

import com.parse.ParsePushBroadcastReceiver;
import android.app.Activity;
import android.app.Notification;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.net.Uri;
import android.os.Bundle;
import android.os.Build.VERSION;
import java.util.Locale;
import java.util.Random;
import org.json.JSONException;
import org.json.JSONObject;
import java.lang.Override;
import android.util.Log;
import com.parse.*;
import android.support.v4.app.TaskStackBuilder;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Build;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;

public class ParsePushReceiver extends ParsePushBroadcastReceiver {
    @Override
    protected int getSmallIconId(Context context, Intent intent) {
        String packageName = context.getPackageName();
        int resId = context.getResources().getIdentifier("notification_icon", "drawable", packageName);

        return resId;
    }

    @Override
    protected Bitmap getLargeIcon(Context context, Intent intent) {
        String packageName = context.getPackageName();
        int largeIconResId = context.getResources().getIdentifier("icon", "drawable", packageName);
        Bitmap largeIconBitmap = BitmapFactory.decodeResource(context.getResources(), largeIconResId);

        return largeIconBitmap;
    }

    @Override
    protected Notification getNotification(Context context, Intent intent) {
        ApplicationInfo ai;
        try {
            ai = context.getPackageManager().getApplicationInfo(context.getPackageName(), 0);
        } catch (final NameNotFoundException e) {
            ai = null;
        }
        final String applicationName = (String) (ai != null ? context.getPackageManager().getApplicationLabel(ai) : "Notification");

        try {
            JSONObject pushData = new JSONObject(intent.getStringExtra("com.parse.Data"));
            if(pushData != null && (pushData.has("alert") || pushData.has("title"))) {
                String title = pushData.optString("title", applicationName);
                String alert = pushData.optString("alert", "Notification received.");
                String tickerText = String.format(Locale.getDefault(), "%s: %s", new Object[]{title, alert});
                Bundle extras = intent.getExtras();
                Random random = new Random();
                int contentIntentRequestCode = random.nextInt();
                int deleteIntentRequestCode = random.nextInt();
                String packageName = context.getPackageName();
                Intent deleteIntent = new Intent("com.parse.push.intent.DELETE");
                deleteIntent.putExtras(extras);
                deleteIntent.setPackage(packageName);
                PendingIntent pDeleteIntent = PendingIntent.getBroadcast(context, deleteIntentRequestCode, deleteIntent, 134217728);

                Intent notificationIntent = new Intent(context, com.epicgames.ue4.GameActivity.class);
                notificationIntent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_SINGLE_TOP);
                PendingIntent pContentIntent = PendingIntent.getActivity(context, contentIntentRequestCode, notificationIntent, 0);

                Notification.Builder noti = new Notification.Builder(context)
                    .setContentTitle(title)
                    .setContentText(alert)
                    .setTicker(tickerText)
                    .setContentIntent(pContentIntent)
                    .setDeleteIntent(pDeleteIntent)
                    .setSmallIcon(this.getSmallIconId(context, intent))
                    .setLargeIcon(this.getLargeIcon(context, intent))
                    .setAutoCancel(true)
                    .setDefaults(-1);

                if(alert != null && alert.length() > 38 && Build.VERSION.SDK_INT >= 16) {
                    noti.setStyle(new Notification.BigTextStyle().bigText(alert));
                }

                Notification buildedNoti;
                if (Build.VERSION.SDK_INT < 16) {
                    buildedNoti = noti.getNotification();
                } else {
                    buildedNoti = noti.build();
                }

                return buildedNoti;
            } else {
                return null;
            }
        } catch (JSONException var3) {
        }
        return null;
    }
}
