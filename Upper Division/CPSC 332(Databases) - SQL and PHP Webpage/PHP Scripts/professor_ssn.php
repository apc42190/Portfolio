<!DOCTYPE html>
<html>
    <body>
        <?php
            $host_name = "mariadb";
            $user = "cs332t10";
            $password = "3K08aBeq";
            $database = "cs332t10";
            
            $SSN = $_POST['SSN'];


            $link = mysqli_connect($host_name, $user, $password, $database);

            if(!$link) {
                die("Could not connect: " . mysqli_connect_error());
            } else {

                $query = "SELECT Title, PLName, ClassRoom Room, MeetDay Day, BegTime Start, EndTime End
                            FROM Professor P, Section S, Meeting M
                            WHERE P.SSN = " . $SSN . " AND P.SSN = S.TeacherSSN AND S.CNum = M.CNum AND S.SecNum = M.SecNum";
                
                $result = mysqli_query($link, $query);

                if (mysqli_num_rows($result) > 0) {

                    echo "<table border='1'>
                    <tr>
                    <th>Title</th>
                    <th>Name</th>
                    <th>Room</th>
                    <th>Day</th>
                    <th>Start Time</th>
                    <th>End Time</th>
                    </tr>";

                    while($row = mysqli_fetch_assoc($result)) {
                        echo "<tr>";
                        echo "<td>" . $row["Title"]; 
                        echo "<td>" . $row["PLName"];   
                        echo "<td>" . $row["Room"];
                        echo "<td>" . $row["Day"];
                        echo "<td>" . $row["Start"];
                        echo "<td>" . $row["End"];
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