<?php 
    if (isset($_POST["name"], $_POST["comment"]))
    {
        $raw_reviews = file_get_contents("reviews.json");
        $json = json_decode($raw_reviews);

        $review = (object)array("name" => htmlspecialchars($_POST["name"]), 
            "comment" => htmlspecialchars($_POST["comment"])
        );

        $json->reviews[] = $review;
        $json = json_encode($json);
        file_put_contents("reviews.json", $json);
    }
    

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