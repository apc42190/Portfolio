<!DOCTYPE html>
<html>
    <body>
        <?php
            $host_name = "mariadb";
            $user = "cs332t10";
            $password = "3K08aBeq";
            $database = "cs332t10";
            
            $course_no = $_POST['course'];


            $link = mysqli_connect($host_name, $user, $password, $database);

            if(!$link) {
                die("Could not connect: " . mysqli_connect_error());
            } else {

                $query = "SELECT S.SecNum Section, ClassRoom Room, MeetDay Day, BegTime Start, EndTime End, COUNT(E.SecNo) AS no_of_student
                          FROM Section S, Meeting M, Enrollment E
                          WHERE S.CNum = " . $course_no . " AND S.SecNum = E.SecNo AND M.SecNum = S.SecNum AND E.ClassNo = S.CNum AND S.CNum = M.CNum
                          GROUP BY Section";
                
                $result = mysqli_query($link, $query);

                if (mysqli_num_rows($result) > 0) {

                    echo "<table border='1'>
                    <tr>
                    <th>Section Number</th>
                    <th>Room</th>
                    <th>Day</th>
                    <th>Start</th>
                    <th>End</th>
                    <th>Students</th>
                    </tr>";

                    while($row = mysqli_fetch_assoc($result)) {
                        echo "<tr>";
                        echo "<td>" . $row["Section"];   
                        echo "<td>" . $row["Room"];   
                        echo "<td>" . $row["Day"];   
                        echo "<td>" . $row["Start"];   
                        echo "<td>" . $row["End"];   
                        echo "<td>" . $row["no_of_student"];   
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