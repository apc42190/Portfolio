<!DOCTYPE html>
<html>
    <body>
        <?php
            $host_name = "mariadb";
            $user = "cs332t10";
            $password = "3K08aBeq";
            $database = "cs332t10";
            
            $CWID = $_POST['CWID'];


            $link = mysqli_connect($host_name, $user, $password, $database);

            if(!$link) {
                die("Could not connect: " . mysqli_connect_error());
            } else {

                $query = "SELECT CTitle, Grade
                          From Course C, Enrollment E
                          WHERE E.SCWID = " . $CWID . " AND C.CNum = E.ClassNo";
                
                $result = mysqli_query($link, $query);

                if (mysqli_num_rows($result) > 0) {

                    echo "<table border='1'>
                    <tr>
                    <th>Course</th>
                    <th>Grade</th>
                    </tr>";

                    while($row = mysqli_fetch_assoc($result)) {
                        echo "<tr>";
                        echo "<td>" . $row["CTitle"];   
                        echo "<td>" . $row["Grade"];
                        echo "</td>";
                    }
                    echo "</table>";

                } else {
                    echo "No results";
                }
            }
            mysqli_close($link);
        ?>
    </body>
</html>