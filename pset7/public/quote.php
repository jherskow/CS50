<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render form
        render("get_quote.php", ["title" => "Quote"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        //get quote
        $_POST = lookup($_POST["symbol"]);
        
        if ($_POST === false)
            {
                apologize("Invalid Symbol. Retry?"); 
            }
        else
            {
                // render quote
                render("show_quote.php", ["title" => "{$_POST["symbol"]} Quote"]);
            }
    }

?>
