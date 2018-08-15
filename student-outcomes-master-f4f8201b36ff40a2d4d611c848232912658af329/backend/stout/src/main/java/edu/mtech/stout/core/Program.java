package edu.mtech.stout.core;

import javax.inject.Named;
import javax.persistence.*;
import java.io.Serializable;
import java.util.Objects;

@Entity
@Table(name = "Program")
@NamedNativeQueries(
  {
    @NamedNativeQuery(
      name = "edu.mtech.stout.core.Program.findAll",
      query = "SELECT * FROM Program",
      resultClass = Program.class
    ),
    @NamedNativeQuery(
      name = "edu.mtech.stout.core.Program.findByName",
      query = "SELECT * FROM Program WHERE name = ?",
      resultClass = Program.class
    ),
    @NamedNativeQuery(
      name = "edu.mtech.stout.core.Program.findByUserId",
      query = "SELECT * FROM Program WHERE program_id in (SELECT Program.program_id" +
        " FROM Program JOIN Program_Permissions ON Program.program_id = Program_Permissions.program_id " +
        "JOIN Users ON Users.user_id = Program_Permissions.user_id WHERE Users.user_id = ?)",
      resultClass = Program.class
    ),
      @NamedNativeQuery(
          name = "edu.mtech.stout.core.Program.findByOffering",
          query = "SELECT * FROM Program WHERE program_id IN " +
              "(SELECT program_id FROM Course JOIN Offering ON Course.course_id = Offering.course_id WHERE offering_id = ?)",
          resultClass = Program.class
      ),
      @NamedNativeQuery(
          name = "edu.mtech.stout.core.Program.findByOfferingStudent",
          query = "SELECT * FROM Program WHERE program_id IN " +
              "(SELECT program_id FROM Course JOIN Offering ON Course.course_id = Offering.course_id " +
              "JOIN Offering_Student ON Offering_Student.offering_id = Offering.offering_id " +
              "WHERE Offering_Student.student_id = ? AND Offering_Student.offering_id = ?)",
          resultClass = Program.class
      ),
      @NamedNativeQuery(
          name = "edu.mtech.stout.core.Program.findByMetric",
          query ="SELECT DISTINCT(Program.program_id) FROM Program JOIN Metric ON Program.program_id = Metric.program_id " +
              "WHERE metric_id = ?",
          resultClass = Program.class
      ),
      @NamedNativeQuery(
          name = "edu.mtech.stout.core.Program.findByPerformance",
          query = "SELECT DISTINCT(Program.program_id) FROM Program JOIN Scale ON Program.program_id = Scale.program_id " +
              "JOIN Perf_Indicator ON Scale.scale_id = Perf_Indicator.scale_id WHERE perf_indicator_id =?",
          resultClass = Program.class
      ),
      @NamedNativeQuery(
          name = "edu.mtech.stout.core.Program.findByStudentId",
          query = "SELECT * FROM Program WHERE program_id IN (SELECT program_id FROM Course JOIN Offering ON Course.course_id = Offering.course_id JOIN Student_Outcome " +
              "ON Offering.offering_id = Student_Outcome.offering_id WHERE Student_Outcome.student_id = ?)",
          resultClass = Program.class
      ),
      @NamedNativeQuery(
          name = "edu.mtech.stout.core.Program.findByStudentAssign",
          query = "SELECT * FROM Program WHERE program_id IN (SELECT program_id FROM Course JOIN Offering On Course.course_id = Offering.course_id " +
              "JOIN Offering_Student ON Offering_Student.offering_id = Offering.offering_id " +
              "JOIN Student_Assign ON Offering_Student.student_id = Student_Assign.student_id " +
              "Where Student_Assign.student_id = ? AND Student_Assign.assign_id = ?)",
          resultClass = Program.class
      )
  })

public class Program  implements Serializable {

  @Id
  @GeneratedValue(strategy = GenerationType.IDENTITY)
  @Column(name = "program_id")
  private long id;

  @Column(name = "name", nullable = false)
  private String name;

  public Program() {
  }

  public Program(String name) {
    this.name = name;
  }

  public long getId() {
    return id;
  }

  public void setId(long id) {
    this.id = id;
  }

  public String getName() {
    return name;
  }

  public void setName(String name) {
    this.name = name;
  }

  @Override
  public boolean equals(Object o) {
    if (this == o) {
      return true;
    }
    if (!(o instanceof Program)) {
      return false;
    }

    final Program that = (Program) o;

    return Objects.equals(this.id, that.id) &&
      Objects.equals(this.name, that.name);
  }

  @Override
  public int hashCode() {
    return Objects.hash(id, name);
  }
}



