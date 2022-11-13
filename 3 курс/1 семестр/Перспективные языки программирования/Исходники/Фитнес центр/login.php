<!DOCTYPE html>
    <html>
        <head>
            <meta charset="utf-8">
            <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
            <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
            <link rel="stylesheet" type="text/css" href="styles.css">

            <title>Login</title>
            <link rel="icon" href="icon.png" />
        </head>
        <body>
            <?php
                session_start();
            ?>

            <nav class="navbar fixed-top navbar-expand-lg navbar-dark bg-dark">
                <a class="navbar-brand" href="index.php">Fitness center Lifeform</a>

                <div class="collapse navbar-collapse">
                    <ul class="navbar-nav mr-auto">
                        <li class="nav-item active">
                            <a class="nav-link" href="doc.pdf" target="_self">Service list</a>
                        </li>
                        <li class="nav-item active">
                            <a class="nav-link" href="contacts.php">Contacts</a>
                        </li>
                    </ul>

                    <ul class="navbar-nav my-lg-0">
                        <li class="nav-item active">
                            <a class="nav-link" href="registration.php">Sign up</a>
                        </li>
                        <li class="nav-item active">
                            <a class="nav-link" href="login.php">Login</a>
                        </li>
                    </ul>
                </div>
            </nav>

            <div class="container text-center">
                <div class="row justify-content-lg-center">
                    <h2>Login</h2>
                </div>

                <div class="text">
                    <?php 
                        if (isset($_POST['login'], $_POST['password']))
                        {
                            $raw_users = file_get_contents("users.json");
                            $json = json_decode($raw_users);
                    
                            $isFound = false;
                            foreach ($json->users as $us)
                            {
                                if ( (strcmp($_POST["login"], $us->login) == 0) && (strcmp($_POST["password"], $us->password) == 0) )
                                {
                                    $isFound = true;
                                    break;
                                }
                            }

                            if ($isFound)
                            {
                                $_SESSION['login'] = $_POST["login"];
                                $_SESSION['password'] = $_POST["password"];
                                header('Location: index.php');
                            }
                            else
                            {
                                echo 'User is not found';
                            }
                        }
                    ?>
                </div>

                <div class="row justify-content-lg-center text">
                    <form action="" method="post" class="text">
                        <p>
                            <label for="login">Login: </label>
                            <input name="login" required>
                        </p>
                        <p>
                            <label for="password">Password: </label>
                            <input type="password" name="password" required>
                        </p>
                        <input type="submit" value="Submit">
                    </form>
                </div>
            </div>
        </body>
    </html>
