<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render form
        render("deposit_form.php", ["title" => "Quote"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        //get quote
        $cash = $_POST["cash"];
        
        if ( ! is_numeric($cash) )
            {
                apologize("Invalid Amount. Retry?"); 
            }
        else
            {
                //update table
                CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?" , $cash , $_SESSION["id"] );
                
                // redirect to portfolio
                redirect("/");
            }
    }

?>
