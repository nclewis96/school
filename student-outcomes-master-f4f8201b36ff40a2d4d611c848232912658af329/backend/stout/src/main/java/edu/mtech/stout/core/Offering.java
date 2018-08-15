package edu.mtech.stout.core;

import javax.persistence.*;
import java.io.Serializable;
import java.util.Objects;

@Entity
@Table(name = "Offering")
@NamedNativeQueries(
  {
    @NamedNativeQuery(
      name = "edu.mtech.stout.core.Offering.findAll",
      query = "SELECT * FROM Offering",
      resultClass = Offering.class
    ),
    @NamedNativeQuery(
      name = "edu.mtech.stout.core.Offering.findByCourse",
      query = "SELECT * FROM Offering WHERE course = ?",
      resultClass = Offering.class
    ),
    @NamedNativeQuery(
      name = "edu.mtech.stout.core.Offering.findByProgramId",
      query = "SELECT * FROM Offering JOIN Course ON Offering.course_id = Course.course_id WHERE Course.program_id = ?",
      resultClass = Offering.class
    ),
      @NamedNativeQuery(
          name = "edu.mtech.stout.core.Offering.findByUser",
          query = "SELECT * FROM Offering WHERE user_id = ?",
          resultClass = Offering.class
      )
  })

public class Offering  implements Serializable {
  @Id
  @GeneratedValue(strategy = GenerationType.IDENTITY)
  @Column(name = "offering_id")
  private long id;
  @Column(name = "course_id", nullable = false)
  private long courseId;
  @Column(name = "user_id", nullable = false)
  private long userId;
  @Column(name = "semester_id", nullable = false)
  private long semesterId;
  @Column(name = "section_num", nullable = false)
  private String sectionNum;
  @Column(name = "locked", nullable = false)
  private boolean locked;
  @Column(name = "num_students", nullable = false)
  private Long numStudents;
  @Column(name = "instructor_name", nullable=true)
  private String instructorName;
  @Column(name = "scale", nullable = true)
  private Long scale;

  public Offering() {
  }

  public long getId() {
    return id;
  }

  public void setId(long id) {
    this.id = id;
  }

  public long getCourseId() {
    return courseId;
  }

  public void setCourseId(long courseId) {
    this.courseId = courseId;
  }

  public long getUserId() {
    return userId;
  }

  public void setUserId(long userId) {
    this.userId = userId;
  }

  public long getSemesterId() {
    return semesterId;
  }

  public void setSemesterId(long semesterId) {
    this.semesterId = semesterId;
  }

  public String getSectionNum() {
    return sectionNum;
  }

  public void setSectionNum(String sectionNum) {
    this.sectionNum = sectionNum;
  }

  public boolean isLocked() {
    return locked;
  }

  public void setLocked(boolean locked) {
    this.locked = locked;
  }

  public Long getNumStudents() {
    return numStudents;
  }

  public void setNumStudents(Long numStudents) {
    this.numStudents = numStudents;
  }


  public String getInstructorName() {
    return instructorName;
  }

  public void setInstructorName(String instructorName) {
    this.instructorName = instructorName;
  }

  public Long getScale() {
    return scale;
  }

  public void setScale(Long scale) {
    this.scale = scale;
  }

  @Override
  public boolean equals(Object o) {
    if (this == o) {
      return true;
    }
    if (!(o instanceof Offering)) {
      return false;
    }

    final Offering that = (Offering) o;

    return Objects.equals(this.id, that.id);
  }

  @Override
  public int hashCode() {
    return Objects.hash(id);
  }

}
