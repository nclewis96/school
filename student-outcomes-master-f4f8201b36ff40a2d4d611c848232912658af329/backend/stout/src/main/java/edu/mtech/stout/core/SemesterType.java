package edu.mtech.stout.core;

import javax.persistence.*;
import java.io.Serializable;
import java.util.Objects;

@Entity
@Table(name = "Semester_Type")
@NamedNativeQueries(
    {
        @NamedNativeQuery(
            name = "edu.mtech.stout.core.SemesterType.findAll",
            query = "SELECT * FROM Semester_Type",
            resultClass = SemesterType.class
        )
    })
public class SemesterType implements Serializable {
  @Id
  @GeneratedValue(strategy = GenerationType.IDENTITY)
  @Column(name = "semester_type_id")
  private long id;
  @Column(name = "text")
  private String text;
  @Column(name = "startMonth")
  private String month;

  public long getId() {
    return id;
  }

  public void setId(long id) {
    this.id = id;
  }

  public String getText() {
    return text;
  }

  public void setText(String text) {
    this.text = text;
  }

  public String getMonth() {
    return month;
  }

  public void setMonth(String month) {
    this.month = month;
  }

  @Override
  public boolean equals(Object o) {
    if (this == o) return true;
    if (!(o instanceof SemesterType)) return false;
    SemesterType that = (SemesterType) o;
    return getId() == that.getId();
  }

  @Override
  public int hashCode() {

    return Objects.hash(getId());
  }
}
