<!DOCTYPE html>
<html>
    <head>
        <title>Result</title>
        <link rel="icon" href="icon.png" />
        <link rel="stylesheet" type="text/css" href="styles.css"/>
    </head>
    <body>
        <?php 
            session_start();
	        session_destroy();
            header('Location: index.php')
        ?>
    </body>
<html>