import React, { Component } from 'react';
import './Question.css';

const Question = (props) => (
      <div>
            <hr/>
            Question {props.qno}
        <div className="form-group">
              <label>Statement</label>
              <input type="text" data-qno={props.qno} className="form-control" value={props.stmnt} onChange={props.StmntChange}/>
        </div>
        <div className="form-group">
              <label>Option1</label>
              <input type="text" data-qno={props.qno} className="form-control" value={props.op1}  onChange={props.Op1Change}/>
        </div>
        <div className="form-group">
              <label>Option2</label>
              <input type="text" data-qno={props.qno} className="form-control" value={props.op2} onChange={props.Op2Change}/>
        </div>
        <div className="form-group">
              <label>Option3</label>
              <input type="text" data-qno={props.qno} className="form-control" value={props.op3} onChange={props.Op3Change}/>
        </div>
        <div className="form-group">
              <label>Option4</label>
              <input type="text" data-qno={props.qno} className="form-control" value={props.op4} onChange={props.Op4Change}/>
        </div>
        <div className="form-group">
              <label>Answer</label>
              <input type="checkbox" data-qno={props.qno} className="form-control" value={1} onClick={props.AnsChange}/>1
              <input type="checkbox" data-qno={props.qno} className="form-control" value={2} onClick={props.AnsChange}/>2
              <input type="checkbox" data-qno={props.qno} className="form-control" value={3} onClick={props.AnsChange}/>3
              <input type="checkbox" data-qno={props.qno} className="form-control" value={4} onClick={props.AnsChange}/>4
              
        </div>
      </div>
            
    );

export default Question;