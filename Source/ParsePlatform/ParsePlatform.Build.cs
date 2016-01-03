// Parse Platform Plugin
// Created by Patryk Stepniewski
// Copyright (c) 2014-2016 gameDNA studio. All Rights Reserved.

using System.IO;

namespace UnrealBuildTool.Rules
{
	public class ParsePlatform : ModuleRules
	{
		private string ModulePath
		{
			get { return Path.GetDirectoryName(RulesCompiler.GetModuleFilename(this.GetType().Name)); }
		}

		public ParsePlatform(TargetInfo Target)
		{
			Definitions.Add("WITH_PARSEPLATFORM=1");

			PublicDependencyModuleNames.AddRange(new string[] { "Engine", "Core", "CoreUObject" });
			PrivateIncludePathModuleNames.AddRange(new string[] { "Settings" });

			// Additional Frameworks and Libraries for iOS
			if (Target.Platform == UnrealTargetPlatform.IOS)
			{
				PublicAdditionalFrameworks.Add(
					new UEBuildFramework(
						"Parse",
						"../../ThirdPartyLibraries/iOS/Parse.embeddedframework.zip"
					)
				);

				PublicAdditionalFrameworks.Add(
				   new UEBuildFramework(
					   "Bolts",
					   "../../ThirdPartyLibraries/iOS/Bolts.embeddedframework.zip"
				   )
				);

				PublicFrameworks.AddRange(
					new string[]
					{
						"Accounts",
						"AudioToolbox",
						"CFNetwork",
						"CoreGraphics",
						"CoreLocation",
						"MobileCoreServices",
						"QuartzCore",
						"Social",
						"Security",
						"StoreKit",
						"SystemConfiguration"
					}
				);

				PublicAdditionalLibraries.Add("z");
				PublicAdditionalLibraries.Add("sqlite3");
			}
			// Additional Frameworks and Libraries for Android
			else if (Target.Platform == UnrealTargetPlatform.Android)
			{
				PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });
				string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, BuildConfiguration.RelativeEnginePath);
				AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", Path.Combine(PluginPath, "ParsePlatform_APL.xml")));
			}
		}
	}
}
