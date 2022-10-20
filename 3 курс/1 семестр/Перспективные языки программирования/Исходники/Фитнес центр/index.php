<!DOCTYPE html>
<html>
    <head>
        <title>Fitness center Lifeform</title>
        <link rel="icon" href="icon.png" />
        <link rel="stylesheet" type="text/css" href="styles.css"/>
    </head>
    <body>
        <h1 class="centered">Fitness center Lifeform</h1>
        <h2 class="centered">News and events</h2>
        <div class="centered">
            <table id="events-table">
                <tr>
                    <td><img src="2.png" /></td>
                    <td><img src="3.png" /></td>
                    <td><img src="4.png" /></td>
                </tr>
                <tr>
                    <td colspan="2" rowspan="2"><img src="1.png" /></td>
                    <td><img src="5.jpg" /></td>
                </tr>
                <tr>
                    <td><img src="6.jpg" /></td>
                </tr>
            </table>
        </div>

        <h2 class="centered">Reviews</h2>
        <table id="reviews" align="center" class="text">
            <?php
                $raw_data = file_get_contents("reviews.json");
                $json = json_decode($raw_data);

                $table_columns = $json->column_names;
                $reviews = $json->reviews;

                echo "<tr>";
                foreach ($table_columns as $column)
                {
                    echo "<td class=\"review-cell\"><b>{$column}</b></td>";
                }     
                echo "</tr>"; 
                        
                foreach ($reviews as $row)
                {
                    echo "<tr><td class=\"review-cell\">{$row->name}</td>";
                    echo "<td class=\"review-cell\">{$row->comment}</td></tr>";
                }
            ?>
        </table>

        <p>
        <h2 class="centered">Send your review</h2>
        <form action="result.php" method="post" class="centered text review-input">
            <p>
                <label for="name">Your name: </label>
                <input name="name" required>
            </p>
            <p>
                <label for="comment">Your comment: </label>
                <input name="comment" id="comment-input" required>
            </p>
            <input type="submit" value="Send">
        </form>
        </p>

        <div id="links" class="text">
            <div class="centered">
                <a href="contacts.html">Contacts</a>
            </div>
            <div class="centered">
                <a href="doc.pdf" target="_self">Download service list</a>
            </div>
        </div>
    </body>
</html>