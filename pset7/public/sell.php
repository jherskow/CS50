<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        //render form SELL
        render("sell_form.php", ["title" => "Sell"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["symbol"]))
            apologize("Please enter a symbol");
        
        $stock = lookup($_POST["symbol"]);

        //find stock in portfolio
        $row = CS50::query("SELECT * FROM portfolios WHERE user_id = ? AND symbol = ?" , $_SESSION["id"] , $_POST["symbol"]  );
        
        $dump = var_dump($row);
        
        if (! empty($row)) 
        {
            
            //figure cash amount
            $sprice = ($stock["price"] * $row[0]["shares"]);
            
            //update datatbase
            CS50::query("DELETE FROM portfolios WHERE user_id = ? AND symbol = ?" , $_SESSION["id"] , $stock["symbol"] );
            CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?" , $sprice , $_SESSION["id"] );
            
            //history update
            CS50::query("INSERT INTO history (user_id, type, symbol, shares, price) VALUES (?,?,?,?,?)" , $_SESSION["id"] ,"sell", $_POST["symbol"] , $_POST["shares"], $stock["price"] );

            // redirect to portfolio
            redirect("/");
            
        }   
        
        else
        {
            apologize("Invalid Symbol. Retry?");
        }
    }

?> 
    

    
