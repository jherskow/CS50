<?php

//load history, check if empty

//if empty error

//else pritn history


    // configuration
    require("../includes/config.php"); 

    //get history
    $rows = CS50::query( "SELECT * FROM `history` WHERE `user_id` = ?" , $_SESSION["id"] ) ;
    
    $history = [];
    
    // check for empty history
    if (empty($rows) )
        $info["empty"] = true;

    else
    {
        $info["empty"] = false;
    //get history and pass to render
    
        foreach ($rows as $row)
        {
            {
                $history[] = [
                    "time" => $row["time"],
                    "type" => $row["type"],
                    "price" => $row["price"],
                    "symbol" => $row["symbol"],
                    "shares" => $row["shares"],
                ];
            }
        }
    }
    
    //get cash balance
    $rows = CS50::query("SELECT * FROM `users` WHERE `id` = ?", $_SESSION["id"]);
    $info["cash"] = $rows[0]["cash"];

    // render portfolio
    render("show_history.php", ["history" => $history, "info" => $info, "title" => "History"]);

?>
