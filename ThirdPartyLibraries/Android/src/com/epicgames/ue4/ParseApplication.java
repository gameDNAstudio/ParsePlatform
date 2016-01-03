// Parse Platform Plugin
// Created by Patryk Stepniewski
// Copyright © 2014-2016 gameDNA studio. All Rights Reserved.

package com.epicgames.ue4;

import android.app.Application;
import android.util.Log;
import com.parse.Parse;
import com.parse.ParseInstallation;
import com.parse.ParsePush;
import android.content.Intent;
import android.os.Bundle;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;

public class ParseApplication extends Application {
    @Override
    public void onCreate() {
        super.onCreate();

        // Parse
        try {
            ApplicationInfo ai = getPackageManager().getApplicationInfo(getPackageName(), PackageManager.GET_META_DATA);
            Bundle bundle = ai.metaData;

            String ParseApplicationId = "";
            String ParseClientKey = "";
            if (bundle.containsKey("com.epicgames.ue4.GameActivity.ParseApplicationId"))
            {
                ParseApplicationId = bundle.getString("com.epicgames.ue4.GameActivity.ParseApplicationId");
            }
            if (bundle.containsKey("com.epicgames.ue4.GameActivity.ParseClientKey"))
            {
                ParseClientKey = bundle.getString("com.epicgames.ue4.GameActivity.ParseClientKey");
            }

            if(ParseApplicationId.length() > 0 && ParseClientKey.length() > 0) {
                Parse.initialize(this, ParseApplicationId, ParseClientKey);
                ParseInstallation.getCurrentInstallation().saveInBackground();
            }
        } catch(Exception e) {
            e.printStackTrace();
        }
    }
}
