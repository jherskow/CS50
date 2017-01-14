<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        //render form BUY
        render("buy_form.php", ["title" => "Buy"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["symbol"]) || empty($_POST["shares"]))
        {
            apologize("Please enter a symbol and number of shares to buy");
        }
        
        $tmp = (int) $_POST["shares"];
        
        if (  $tmp != $_POST["shares"]  || $_POST["shares"] <= 0 )
        {
            apologize("Shares must be a positive integer");
        }
        
        $stock = lookup($_POST["symbol"]);

        if ($stock == false)
        {
            apologize("Invalid Symbol. Retry?"); 
        }
        else
        {
            // BUY
            
            //symbol to uppercase
            $_POST["symbol"] = $stock["symbol"];
            
            //figure cash amount
            $sprice = ($stock["price"] * $_POST["shares"] );
            
            //CHECK ENOUGH CASH
            $row = CS50::query("SELECT * FROM users WHERE id = ?" , $_SESSION["id"] );
            if ($row[0]["cash"] < $sprice)
            {
                apologize("Insufficient funds. Retry?");
            }

                //update cash
                CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?" , $sprice , $_SESSION["id"] );
            
            
                //add to portfolio
                CS50::query("INSERT INTO portfolios (user_id, symbol, shares) VALUES (?,?,?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)" , $_SESSION["id"] , $_POST["symbol"] , $_POST["shares"] );

                //history update
                CS50::query("INSERT INTO history (user_id, type, symbol, shares, price) VALUES (?,?,?,?,?)" , $_SESSION["id"] ,"buy", $_POST["symbol"] , $_POST["shares"], $stock["price"] );

        }
    // redirect to portfolio
    redirect("/");  
    }

?> 
    

    
