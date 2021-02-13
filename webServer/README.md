Very simply a default apache web server that only serves up its index.html file. This index file presents ‘currentStatus.png’, which is a copy of the most recent plot. The Recording program writes this to /var/www/html/currentStatus.png
https://www.raspberrypi.org/documentation/remote-access/web-server/apache.md

The index.html is simply:
<!DOCTYPE html>
<html>
<meta http-equiv="Cache-Control" content="no-cache, no-store, must-revalidate">
   <head>
      <title>Using Image in Webpage</title>
   </head>
	
   <body>
      <p>Simple Image Insert</p>
      <img src = "/html/images/currentStatus.png" alt = "Test Image" />
   </body>
	
</html>


Recording
Create a generic sim link from the generated .png to high-level location:
ln -s /var/SaunaPiData/2021/Dec/2021-Dec-1.png /var/SaunaPiData/currentStatus.png


From within the /var/www/html dir, create a sim link to the generic link created above:
sudo ln -s /var/SaunaPiData/currentStatus.png currentStatus.png

Now we don’t have to fool with updates to /var/www/html permissions.
