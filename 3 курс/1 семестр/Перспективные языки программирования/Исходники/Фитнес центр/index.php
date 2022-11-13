<!doctype html>
<html>
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
        <link rel="stylesheet" type="text/css" href="styles.css">
        
        <title>Fitness center Lifeform</title>
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
                 <h2>News and events</h2>
            </div>
        </div>

        <table class="table table-borderedless">
            <tbody>
                <tr>
                    <td><img src="2.png" class="img-fluid"/></td>
                    <td><img src="3.png" class="img-fluid"/></td>
                    <td><img src="4.png" class="img-fluid"/></td>
                </tr>
                <tr>
                    <td><img src="1.png" class="img-fluid"/></td>
                    <td><img src="5.png" class="img-fluid"/></td>
                    <td><img src="6.png" class="img-fluid"/></td>
                </tr>
            </tbody>
        </table>

        <div class="container">
            <div class="row justify-content-lg-center">
                <h2>Reviews</h2>
            </div>

            <div class="row justify-content-lg-center">
                    <table id="reviews" class="table text">
                        <div id="reviews-content"></div>
                    </table>
            </div>
        </div>

        <div class="container text-center">
            <?php if ( !isset($_SESSION['login'], $_SESSION['password'])): ?>
                <div class="row justify-content-lg-center">
                    <h2>Log in to send review</h2>
                </div>
            <?php else: ?>
                <div class="row justify-content-lg-center">
                <h2>Send your review</h2>
            </div>
                <div class="row justify-content-lg-center text">
                    <form class="text">
                        <input type="hidden" id="review-name" name="name" value= <?php echo $_SESSION['login']; ?>>
                        <p>
                            <label for="comment">Your comment: </label>
                            <input id="review-comment" name="comment" required>
                        </p>
                        <input type="button" id="review-send" value="Send">
                    </form>
                </div>
            <?php endif; ?>
        </div>

        <script src="https://code.jquery.com/jquery-3.2.1.slim.min.js" integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" crossorigin="anonymous"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
        <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js" integrity="sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl" crossorigin="anonymous"></script>

        <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.9.1/jquery.min.js"></script>
        <script src="ajax.js"></script>
    </body>
</html>