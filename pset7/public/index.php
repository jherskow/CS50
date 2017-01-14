<?php

    // configuration
    require("../includes/config.php"); 

    //get portfolio
    $rows = CS50::query( "SELECT * FROM `portfolios` WHERE `user_id` = ?" , $_SESSION["id"] ) ;
    
    $positions = [];
    
    // check for empty portfolio
    if (empty($rows) )
        $info["empty"] = true;

    else
    {
        $info["empty"] = false;
    //get positions and pass to render
    
        foreach ($rows as $row)
        {
            $stock = lookup($row["symbol"]);
            if ($stock !== false)
            {
                $positions[] = [
                    "name" => $stock["name"],
                    "price" => $stock["price"],
                    "shares" => $row["shares"],
                    "symbol" => $row["symbol"]
                ];
            }
        }
    }
    
    //get cash balance
    $rows = CS50::query("SELECT * FROM `users` WHERE `id` = ?", $_SESSION["id"]);
    $info["cash"] = $rows[0]["cash"];

    // render portfolio
    render("portfolio.php", ["positions" => $positions, "info" => $info, "title" => "Portfolio"]);

?>
