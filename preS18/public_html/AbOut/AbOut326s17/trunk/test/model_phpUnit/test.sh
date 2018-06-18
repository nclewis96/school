mysql -u "web_user" "-presu_bew" "AbOut_Test"  --force < "AbOut_PHPTest.sql"
sed -i.bak 's/AbOut_2014/AbOut_Test/g' ../../application/includes/startup.php
phpunit PHP_Tests
sed -i.bak 's/AbOut_Test/AbOut_2014/g' ../../application/includes/startup.php
