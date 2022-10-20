<!DOCTYPE html>
<html>
    <head>
        <title>Result</title>
        <link rel="icon" href="icon.png" />
        <link rel="stylesheet" type="text/css" href="styles.css"/>
    </head>
    <body>
        <?php 
            $raw_reviews = file_get_contents("reviews.json");
            $json = json_decode($raw_reviews);

            $review = (object)array("name" => htmlspecialchars($_POST["name"]), 
                "comment" => htmlspecialchars($_POST["comment"])
            );

            $json->reviews[] = $review;
            $json = json_encode($json);
            file_put_contents("reviews.json", $json);
            header('Location: index.php')
        ?>
    </body>
<html>