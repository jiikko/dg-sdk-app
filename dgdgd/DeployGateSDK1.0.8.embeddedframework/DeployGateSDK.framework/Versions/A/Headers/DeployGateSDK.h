//
//  DeployGateSDK.h
//  DeployGateSDK Version 1.0.8
//
//  Created by DeployGate on 05/11/13.
//  Copyright 2015 DeployGate Inc. All rights reserved.

#import <Foundation/Foundation.h>

@interface DeployGateSDK : NSObject

/**
 * If SDK reports crash logs on DeployGate. Note that crash logs are sent after the application did finish the next launching.
 * Crash logs are generated by [PLCrashReporter](https://code.google.com/p/plcrashreporter/). It is a reliable open soruce crash report framework.
 * Note that SDK doesn't send Crash Report at the crash time but next launch.
 *
 * Default: _NO_
 */
@property(nonatomic) BOOL crashReportDisabled;

/**
 * Provides if you allowed SDK to report launching this app on DeployGate.
 *
 * Default: _NO_
 */
@property(nonatomic) BOOL appBootReportDisabled;

/**
 * Provides if you allowed SDK to report launching this app on DeployGate.
 * This feature is not implmented as push notification.
 * SDK checks latest revision from deploygate.com at the launching time.
 * Note that you need to set YES to userInformationEnabled to alert Update Check.
 *
 * Default: _NO_
 */
@property(nonatomic) BOOL appUpdateCheckDisabled;

/**
 * If the user downloading this app is authenticated on the Deploygate.
 *
 * Default: _NO_
 */
@property(nonatomic, readonly) BOOL userAuthorization;

/**
 * DeployGate Options
 * Sets this options to 'options' property.
 *
 */
typedef enum DeployGateSDKOption : NSUInteger {
    DeployGateSDKOptionDisableLogToConsole   = (1 << 0), // => 00000001
    DeployGateSDKOptionDisableBackgroundInfo = (1 << 1)  // => 00000010
} DeployGateSDKOption;

/*
 * If SDK outputs DGSLog on Xcode console.
 * If SDK outputs Background Infomation on Xcode console.
 * Default: 0
 */
@property(nonatomic) DeployGateSDKOption options;

/*
 * If the property is set YES, All the methods in DeployGate SDK class doesn't work.
 * You need to set YES, when you build the app for release.
 * Default: _NO_
 */
@property(nonatomic) BOOL terminated;

/*
 * Get the shared instance of the DeployGateSDK class.
 */
+ (DeployGateSDK*)sharedInstance;

/*
 * Get DeployGate iOS SDK version.
 */
+ (NSString*)version;

/**
 * Starts DeployGate session using the onwer name and her/his api key.
 * @param author owner name for this application
 * @param apiKey api key of the owner
 */
- (void)launchApplicationWithAuthor:(NSString*)author key:(NSString*)apiKey;

/**
 * Starts DeployGate session using the onwer name and her/his api key.
 * You can choose whether SDK use user information in your app or not.
 *
 * When you set _YES_ to userInfomationEnabled, your app transit to
 * mobile safari and get back with the user information.
 *
 * @param author owner name for this application
 * @param apiKey api key of the owner
 * @param userInfomationEnabled If SDK use user information on DeployGate.
 */
- (void)launchApplicationWithAuthor:(NSString *)author
                                key:(NSString *)apiKey
              userInfomationEnabled:(BOOL)userInfomationEnabled;

/**
 * Asks SDK to open callback from mobile safari.
 * If you set _YES_ on launchDisabled property, SDK does nothing in this method and returns _NO_.
 * @param url The URL resource to open. SDK can open only DeployGate URL Scheme you set.
 * @param sourceApplication The Bundle ID of the app that is requesting your app to open the URL.
 * @param annotation A property-list object supplied by the source app to communicate information to the receiving app.
 */
- (BOOL)handleOpenUrl:(NSURL*)url
    sourceApplication:(NSString*)sourceApplication
           annotation:(id)annotation;

/**
 * Asks SDK to open callback from mobile safari.
 * If you set _YES_ on launchDisabled property, SDK does nothing in this method.
 * @param url The URL resource to open. SDK can open only DeployGate URL Scheme you set.
 */
- (void)handleOpenUrl:(NSURL*)url;

/**
 * Checks if the author has still allowed the user to use this app on DeployGate.
 * You can execute a block before check user authorization.
 * If you set _YES_ on launchDisabled property, SDK does nothing in this method.
 * Note that the handler passes _NO_, when SDK doesn't know who is using this app.
 * @param handler The handler block to catch the result.
 */
- (void)userAuthorizationWithCompletionHandler:(void (^)(BOOL authorized, NSError *error))handler;

@end

/*
 * Remote Logging. DGSLog doesn't only log to DeployGate, but also log to Xcode console.
 * If you set YES on launchDisabled property, DGSLog logs only to the console .
 * Note that SDK stores logs in an internal file and send it at the next launch.
 * Logs are stored in a file with [CocoaLumberjack](https://github.com/CocoaLumberjack/CocoaLumberjack). It is a reliable open soruce log framework.
 *
 */
FOUNDATION_EXPORT void DGSLog(NSString* format, ...);
FOUNDATION_EXPORT void DGSLogv(NSString* format, va_list args);
