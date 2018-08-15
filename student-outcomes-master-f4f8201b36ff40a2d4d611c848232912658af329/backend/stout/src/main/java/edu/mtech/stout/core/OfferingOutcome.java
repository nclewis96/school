package edu.mtech.stout.core;

import org.hibernate.SessionFactory;

import javax.persistence.*;
import java.io.Serializable;
import java.util.Objects;

@Entity
@Table(name = "Offering_Outcome")
@NamedNativeQueries(
    {
        @NamedNativeQuery(
            name = "edu.mtech.stout.core.OfferingOutcome.findAll",
            query = "SELECT * FROM Offering_Outcome",
            resultClass =  OfferingOutcome.class
        ),
        @NamedNativeQuery(
            name = "edu.mtech.stout.core.OfferingOutcome.findProgramId",
            query = "SELECT * FROM Offering_Outcome JOIN Offering ON Offering_Outcome.offering_id = Offering.offering_id " +
                "JOIN Course ON Offering.course_id = Course.course_id WHERE Course.program_id = ?",
            resultClass = OfferingOutcome.class
        )
    })

public class OfferingOutcome implements Serializable{
  @Id
  @Column(name = "offering_id")
  private long offeringId;
  @Id
  @Column(name = "outcome_id")
  private long outcomeId;
  @Column(name = "score")
  private double score;

  public OfferingOutcome(){
    super();
  }

  public OfferingOutcome(long offeringId, long outcomeId){
    this.offeringId = offeringId;
    this.outcomeId = outcomeId;
  }
  public long getOfferingId() {
    return offeringId;
  }

  public void setOfferingId(long offeringId) {
    this.offeringId = offeringId;
  }

  public long getOutcomeId() {
    return outcomeId;
  }

  public void setOutcomeId(long outcomeId) {
    this.outcomeId = outcomeId;
  }

  public double getScore() {
    return score;
  }

  public void setScore(double score) {
    this.score = score;
  }

  @Override
  public boolean equals(Object o) {
    if (this == o) return true;
    if (!(o instanceof OfferingOutcome)) return false;
    OfferingOutcome that = (OfferingOutcome) o;
    return getOfferingId() == that.getOfferingId() &&
        getOutcomeId() == that.getOutcomeId();
  }

  @Override
  public int hashCode() {

    return Objects.hash(getOfferingId(), getOutcomeId());
  }
}
