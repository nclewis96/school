package edu.mtech.stout.core;

import jdk.jfr.Name;

import javax.persistence.*;
import java.io.Serializable;
import java.util.Objects;

@Entity
@Table(name = "Outcome_Assign")
@NamedNativeQueries({
    @NamedNativeQuery(
        name = "edu.mtech.stout.core.OutcomeAssign.findAll",
        query = "SELECT * FROM Outcome_Assign",
        resultClass = OutcomeAssign.class
    )
})
public class OutcomeAssign implements Serializable{
  @Id
  @Column(name = "outcome_id")
  private long outcomeId;
  @Id
  @Column(name = "assign_id")
  private long assignId;

  public OutcomeAssign(){ super();}

  public OutcomeAssign(long outcomeId, long assignId){
    this.outcomeId = outcomeId;
    this.assignId = assignId;
  }

  public long getOutcomeId() {
    return outcomeId;
  }

  public void setOutcomeId(long outcomeId) {
    this.outcomeId = outcomeId;
  }

  public long getAssignId() {
    return assignId;
  }

  public void setAssignId(long assignId) {
    this.assignId = assignId;
  }

  @Override
  public boolean equals(Object o) {
    if (this == o) return true;
    if (!(o instanceof OutcomeAssign)) return false;
    OutcomeAssign that = (OutcomeAssign) o;
    return getOutcomeId() == that.getOutcomeId() &&
        getAssignId() == that.getAssignId();
  }

  @Override
  public int hashCode() {

    return Objects.hash(getOutcomeId(), getAssignId());
  }
}
