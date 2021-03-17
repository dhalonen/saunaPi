Very simply a default apache web server that only serves up its index.html file. This index file presents ‘currentStatus.png’, which is a copy of the most recent plot. The RaspberryPi program writes this to /var/www/html/currentStatus.png.

Installation of webserver is documented here:
https://www.raspberrypi.org/documentation/remote-access/web-server/apache.md

The index.html is simply:
```
<!DOCTYPE html>
<head>
  <script type="text/javascript">
    function stamp()
    {
      var node = document.getElementById('plot');
      node.attributes['src'].value += "?a=" + Math.random().toString();
    }
  </script>
<head>
<html>
  <meta http-equiv="Cache-Control" content="no-cache, no-store, must-revalidate">

   <head>
      <title>Using Image in Webpage</title>
   </head>

   <body onload="stamp();">
      <img id="plot" src = "currentStatus.png" alt = "Test Image" />
   </body>

</html>
```

Use a bit of indirection to get the 'currentStatus.png' updated w/o copying or moving files. Also, gets around permission resets.

Create a generic sim link from the newly generated .png to high-level location:
ln -s /var/SaunaPiData/2021/Dec/2021-Dec-1.png /var/SaunaPiData/currentStatus.png


From within the /var/www/html dir, create a sim link to the generic link created above:
sudo ln -s /var/SaunaPiData/currentStatus.png currentStatus.png

Now we don’t have to fool with updates to /var/www/html permissions.

Note the addition of "?a=" + Math.random().toString() to the image src tag. This is because Safari on iOS doesn't seem to want to update the image with every refresh. By adding a random string to the tag, the current image is always presented.


In order to get the iPhone to read current conditions, all that's necessary is: http://saunapi.harmon/data.json

However, a symbolic link is helpful again. In this case:

```
cd /var/www/html
ln -s /var/SaunaPi/saunapidata.json data.json
```

Now the SaunaPi app updates /var/SaunaPi/saunapidata.json with temperature & timestamp. The iPhone merely executes the http query and parses the json for presentation.
