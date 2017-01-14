<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["username"]))
            apologize("Please enter a Username.");
        if (empty($_POST["password"]))
            apologize("Please enter a password.");
        if ($_POST["confirmation"] != $_POST["password"])
            apologize("The Password you have entered does not match your password confirmation. please try again.");
        
        $success = CS50::query("INSERT IGNORE INTO users (username, hash, cash) VALUES(?, ?, 10000.0000)", $_POST["username"], password_hash($_POST["password"], PASSWORD_DEFAULT));
        
        if ( $success == 0)
            {
            apologize("The useranme BLARG is taken or invalid. please try again.");
            }
        else
            {
                $rows = CS50::query("SELECT LAST_INSERT_ID() AS id");
                $id = $rows[0]["id"];
                $_SESSION["id"] = $id;
                redirect("/");
            }


    }

?> 
    

    
