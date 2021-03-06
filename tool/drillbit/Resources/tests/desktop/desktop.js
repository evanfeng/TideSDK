/**
 * Copyright (c) 2012 - 2014 TideSDK contributors 
 * http://www.tidesdk.org
 * Includes modified sources under the Apache 2 License
 * Copyright (c) 2008 - 2012 Appcelerator Inc
 * Refer to LICENSE for details of distribution and use.
 **/

describe("Desktop tests", {
  test_desktop_functions: function () {
    value_of(Ti.Desktop.openApplication)
      .should_be_function();
    value_of(Ti.Desktop.openURL)
      .should_be_function();
    value_of(Ti.Desktop.takeScreenshot)
      .should_be_function();
  },
  test_screenshot: function () {
    // not implemented in linux yet
    if (Ti.platform == "linux") return;

    var invalid_args = false;
    try {
      Ti.Desktop.takeScreenshot();
    } catch (e) {
      invalid_args = true;
    }

    value_of(invalid_args)
      .should_be_true();

    var ext = "png";
    if (Ti.platform == "win32") {
      ext = "bmp";
    }

    var appdir = Ti.Filesystem.getApplicationDataDirectory();
    var file = Ti.Filesystem.getFile(appdir, "screenshot." + ext);
    Ti.Desktop.takeScreenshot(file.nativePath());

    value_of(file.exists())
      .should_be_true();
  }
});
