package edu.mtech.stout.core;

import javax.persistence.*;
import java.io.Serializable;
import java.util.Date;
import java.util.Objects;

@Entity
@Table(name = "Program_Cutoff")
@NamedNativeQueries(
    {
        @NamedNativeQuery(
          name = "edu.mtech.stout.core.ProgramCutoff.findAll",
            query = "SELECT * FROM Program_Cutoff",
            resultClass = ProgramCutoff.class
        ),
        @NamedNativeQuery(
            name = "edu.mtech.stout.core.ProgramCutoff.findByProgram",
            query = "SELECT * FROM Program_Cutoff WHERE program_id = ?",
            resultClass = ProgramCutoff.class
        )
    })
public class ProgramCutoff implements Serializable{
  @Id
  @Column(name = "program_id")
  private long programId;
  @Id
  @Column(name = "semester_id")
  private long semesterId;
  @Column(name = "start_date")
  private Date start;
  @Column(name = "end_date")
  private Date end;

  public ProgramCutoff(){
    super();
  }

  public ProgramCutoff(long programId, long semesterId){
    this.programId = programId;
    this.semesterId = semesterId;
  }

  public long getProgramId() {
    return programId;
  }

  public void setProgramId(long programId) {
    this.programId = programId;
  }

  public long getSemesterId() {
    return semesterId;
  }

  public void setSemesterId(long semesterId) {
    this.semesterId = semesterId;
  }

  public Date getStart() {
    return start;
  }

  public void setStart(Date start) {
    this.start = start;
  }

  public Date getEnd() {
    return end;
  }

  public void setEnd(Date end) {
    this.end = end;
  }

  @Override
  public boolean equals(Object o) {
    if (this == o) return true;
    if (!(o instanceof ProgramCutoff)) return false;
    ProgramCutoff that = (ProgramCutoff) o;
    return getProgramId() == that.getProgramId() &&
        getSemesterId() == that.getSemesterId();
  }

  @Override
  public int hashCode() {

    return Objects.hash(getProgramId(), getSemesterId());
  }
}
