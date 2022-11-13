<!DOCTYPE html>
    <html>
        <head>
            <meta charset="utf-8">
            <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
            <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
            <link rel="stylesheet" type="text/css" href="styles.css">

            <title>Contacts</title>
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
                            <a class="nav-link" href="contacts.html">Contacts</a>
                        </li>
                    </ul>

                    <?php if ( !isset($_SESSION['login'], $_SESSION['password'])): ?>
                        <ul class="navbar-nav my-lg-0">
                            <li class="nav-item active">
                                <a class="nav-link" href="registration.php">Sign up</a>
                            </li>
                            <li class="nav-item active">
                                <a class="nav-link" href="login.php">Login</a>
                            </li>
                        </ul>
                    <?php else: ?>
                        <ul class="navbar-nav my-lg-0">
                            <li class="nav-item active">
                                <a class="nav-link" href="#"><?php echo $_SESSION['login']; ?></a>
                            </li>
                            <li class="nav-item active">
                                <a class="nav-link" href="logout.php">Log out</a>
                            </li>
                        </ul>
                    <?php endif; ?>
                </div>
            </nav>

            <div class="container">
                <div class="row justify-content-lg-center">
                    <h2>Our contacts</h2>
                </div>
                <div class="row justify-content-lg-center text">
                    <ul>
                        <li>VK - vk.com/lifeform</li>
                        <li>Mail - info@lifeform.ru </li>
                        <li>Telegram - @lifeform</li>
                        <li>WhatsApp - 79651234567</li>
                    </ul>
                </div>
            </div>
        </body>
    </html>
