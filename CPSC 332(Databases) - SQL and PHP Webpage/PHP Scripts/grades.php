<!DOCTYPE html>
<html>
    <body>
        <?php
            $host_name = "mariadb";
            $user = "cs332t10";
            $password = "3K08aBeq";
            $database = "cs332t10";
            
            $course_no = $_POST['course'];
            $sec_no = $_POST['section'];



            $link = mysqli_connect($host_name, $user, $password, $database);

            if(!$link) {
                die("Could not connect: " . mysqli_connect_error());
            } else {

                $query = "SELECT Grade, COUNT(Grade) AS Number_of_Appearances
                          FROM Enrollment E 
                          WHERE E.ClassNo = " . $course_no . " AND E.SecNo = " . $sec_no . 
                          " GROUP BY Grade";
                
                $result = mysqli_query($link, $query);

                if (mysqli_num_rows($result) > 0) {

                    echo "<table border='1'>
                    <tr>
                    <th>Grade</th>
                    <th>Count</th>
                    </tr>";

                    while($row = mysqli_fetch_assoc($result)) {
                        echo "<tr>";
                        echo "<td>" . $row["Grade"];   
                        echo "<td>" . $row["Number_of_Appearances"];
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