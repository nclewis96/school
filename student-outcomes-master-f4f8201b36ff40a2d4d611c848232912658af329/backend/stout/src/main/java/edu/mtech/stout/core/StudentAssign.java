package edu.mtech.stout.core;


import jdk.jfr.Name;

import javax.persistence.*;
import java.io.Serializable;
import java.util.Objects;

@Entity
@Table(name = "Student_Assign")
@NamedNativeQueries(
    {
        @NamedNativeQuery(
            name = "edu.mtech.stout.core.StudentAssign.findAll",
            query = "SELECT * FROM Student_Assign",
            resultClass =  StudentAssign.class
        ),
        @NamedNativeQuery(
            name = "edu.mtech.stout.core.StudentAssign.findByProgramId",
            query = "SELECT DISTINCT(student_id) FROM Student_Assign JOIN Offering_Assign ON Student_Assign.assign_id = Offering_Assign.assign_id " +
                "JOIN Offering ON Offering_Assign.offering_id = Offering.offering_id JOIN Course ON Offering.course_id = Course.course_id " +
                "WHERE Course.program_id = ?",
            resultClass = StudentAssign.class
        ),
        @NamedNativeQuery(
            name = "edu.mtech.stout.core.StudentAssign.findByUserId",
            query = "SELECT DISTINCT(student_id) FROM Student_Assign JOIN Offering_Assign ON Student_Assign.assign_id = Offering_Assign.assign_id " +
                "JOIN Offering ON Offering_Assign.offering_id = Offering.offering_id WHERE Offering.user_id = ?",
            resultClass = StudentAssign.class
        )
    }
)
public class StudentAssign implements Serializable {
  @Id
  @Column(name = "student_id")
  private long studentId;
  @Id
  @Column(name = "assign_id")
  private long assignId;
  @Column(name = "score")
  private int score;

  public StudentAssign(){
    super();
  }

  public StudentAssign(long studentId, long assignId){
    this.studentId = studentId;
    this.assignId = assignId;
  }

  public long getStudentId() {
    return studentId;
  }

  public void setStudentId(long studentId) {
    this.studentId = studentId;
  }

  public long getAssignId() {
    return assignId;
  }

  public void setAssignId(long assignId) {
    this.assignId = assignId;
  }

  public int getScore() {
    return score;
  }

  public void setScore(int score) {
    this.score = score;
  }

  @Override
  public boolean equals(Object o) {
    if (this == o) return true;
    if (!(o instanceof StudentAssign)) return false;
    StudentAssign that = (StudentAssign) o;
    return getStudentId() == that.getStudentId() &&
        getAssignId() == that.getAssignId();
  }

  @Override
  public int hashCode() {
    return Objects.hash(getStudentId(), getAssignId() );
  }
}
