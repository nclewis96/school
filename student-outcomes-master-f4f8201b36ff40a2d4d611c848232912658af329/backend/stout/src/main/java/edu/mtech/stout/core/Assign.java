package edu.mtech.stout.core;

import javax.persistence.*;
import java.io.Serializable;
import java.util.Objects;


@Entity
@Table(name = "Offering_Assign")
@NamedNativeQueries(
  {
    @NamedNativeQuery(
      name = "edu.mtech.stout.core.Assign.findAll",
      query = "SELECT * FROM Offering_Assign",
      resultClass = Assign.class
    ),
      @NamedNativeQuery(
          name = "edu.mtech.stout.core.Assign.findProgramId",
          query = "SELECT * FROM Offering_Assign JOIN Offering ON Offering_Assign.offering_id=Offering.offering_id" +
              " JOIN Course ON Offering.course_id = Course.course_id WHERE Course.program_id = ?",
          resultClass = Assign.class
      )
  })
public class Assign  implements Serializable {
  @Id
  @GeneratedValue(strategy = GenerationType.IDENTITY)
  @Column(name = "assign_id")
  private long id;
  @Column(name = "offering_id")
  private long offeringId;
  @Column(name = "score")
  private long score;
  @Column(name = "name")
  private String name;
  @Column(name = "desc")
  private String desc;
  @Column(name = "max_score")
  private long maxScore;

  public long getId() {
    return id;
  }

  public void setId(long id) {
    this.id = id;
  }

  public long getOfferingId() {
    return offeringId;
  }

  public void setOfferingId(long offeringId) {
    this.offeringId = offeringId;
  }

  public long getScore() {
    return score;
  }

  public void setScore(long score) {
    this.score = score;
  }

  public String getName() {
    return name;
  }

  public void setName(String name) {
    this.name = name;
  }

  public String getDesc() {
    return desc;
  }

  public void setDesc(String desc) {
    this.desc = desc;
  }

  public long getMaxScore() {
    return maxScore;
  }

  public void setMaxScore(long maxScore) {
    this.maxScore = maxScore;
  }

  @Override
  public boolean equals(Object o) {
    if (this == o) {
      return true;
    }
    if (!(o instanceof Assign)) {
      return false;
    }

    final Assign that = (Assign) o;

    return Objects.equals(this.id, that.id) &&
      Objects.equals(this.offeringId, that.offeringId);
  }

  @Override
  public int hashCode() {
    return Objects.hash(id, offeringId);
  }
}
