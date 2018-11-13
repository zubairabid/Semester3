import React, { Component } from 'react';
import './CreateQuiz.css';
import Redirect from 'react-router-dom/Redirect';

class CreateQuiz extends Component {
  constructor() {
    super();
    this.state = {
      formData: {
        genre: "",
        quests: [],
      },
      submitted: false,
      no_of_ques: 0,
  }
    this.initialstate=this.state
    this.handleGChange = this.handleGChange.bind(this);
    this.handleQnoIChange = this.handleQnoIChange.bind(this);
    this.handleQnoDChange = this.handleQnoDChange.bind(this);
    this.handleSubmit = this.handleSubmit.bind(this);
    this.handleSChange = this.handleSChange.bind(this);
    this.handleOp1Change = this.handleOp1Change.bind(this);
    this.handleOp2Change = this.handleOp2Change.bind(this);
    this.handleOp3Change = this.handleOp3Change.bind(this);
    this.handleOp4Change = this.handleOp4Change.bind(this);
    this.handleAChange = this.handleAChange.bind(this);
  }

  handleSubmit (event) {
    event.preventDefault();
    var sent_json
    sent_json=JSON.parse(JSON.stringify(this.state.formData));
    var i
    for(i=0;i<sent_json.quests.length;i++){
       sent_json.quests[i].answer=JSON.stringify(sent_json.quests[i].answer)
       sent_json.quests[i].options=JSON.stringify(sent_json.quests[i].options)
    }
    
    console.log(sent_json)
    fetch('http://localhost:8080/quizzes', {
     method: 'POST',
     body: JSON.stringify(sent_json),
   })
      .then(response => {
        if(response.status >= 200 && response.status < 300){
          this.setState(this.initialstate);
          alert('Quiz Created Successfully')
          window.location.reload()
        }
      });
  }

  handleGChange(event) {
    this.state.formData.genre = event.target.value
  }
  handleQnoIChange() {
    var temp
    temp = this.state.no_of_ques + 1
    this.state.formData.quests.push({statement:"", options:["","","",""], answer:[false,false,false,false]})
    this.setState({no_of_ques:temp})
    console.log(this.state.formData)

  }
  handleQnoDChange() {
    var temp
    if(this.state.no_of_ques>0){ temp = this.state.no_of_ques - 1;
      this.state.formData.quests.pop()
      console.log(temp)  
    }
    else{ temp=0;}
    this.setState({no_of_ques:temp})

  }
  handleSChange(event){
    this.state.formData.quests[event.target.getAttribute('data-qno')-1].statement = event.target.value 

  }
  handleOp1Change(event){
    console.log(event.target.getAttribute('data-qno'))
    this.state.formData.quests[event.target.getAttribute('data-qno')-1].options[0] = event.target.value

  }
  handleOp2Change(event){
    this.state.formData.quests[event.target.getAttribute('data-qno')-1].options[1] = event.target.value
    
  }
  handleOp3Change(event){
    this.state.formData.quests[event.target.getAttribute('data-qno')-1].options[2] = event.target.value
    
  }
  handleOp4Change(event){
    this.state.formData.quests[event.target.getAttribute('data-qno')-1].options[3] = event.target.value
    
  }
  handleAChange(event){
    var temp
    temp = this.state.formData.quests[event.target.getAttribute('data-qno')-1].answer[event.target.value-1]
    this.state.formData.quests[event.target.getAttribute('data-qno')-1].answer[event.target.value-1]=!temp
  }
  
  render() {

    if(localStorage.getItem("LoggedIn")==="true" &&!(localStorage.getItem("userlogged")==="admin")){
      return(<Redirect to="/" />)
    }

    var rows = [], i = 0, len = this.state.no_of_ques;
    while (++i <= len) rows.push(i);
    return (
      <div className="App">
        <header className="App-header">
          <h1 className="App-title">Create a New Quiz</h1>
        </header>
        <br/><br/>
        <div className="formContainer">
          <form onSubmit={this.handleSubmit}>
            <div className="form-group">
                <label>Genre</label>
                <input type="text" className="form-control" value={this.state.genre} onChange={this.handleGChange}/>
            </div>
            <button type="button" className="btn btn-default" onClick={this.handleQnoIChange}>+</button>
            <button type="button" className="btn btn-default" onClick={this.handleQnoDChange}>-</button>


              {rows.map(function (i) {
                return (
                <div>
                <hr/>
                          Question {i}
                      <div className="form-group">
                            <label>Statement</label>
                            <input type="text" data-qno={i} className="form-control" onChange={this.handleSChange}/>
                      </div>
                      <div className="form-group">
                            <label>Option1</label>
                            <input type="text" data-qno={i} className="form-control" onChange={this.handleOp1Change}/>
                      </div>
                      <div className="form-group">
                            <label>Option2</label>
                            <input type="text" data-qno={i} className="form-control" onChange={this.handleOp2Change}/>
                      </div>
                      <div className="form-group">
                            <label>Option3</label>
                            <input type="text" data-qno={i} className="form-control"  onChange={this.handleOp3Change}/>
                      </div>
                      <div className="form-group">
                            <label>Option4</label>
                            <input type="text" data-qno={i} className="form-control"  onChange={this.handleOp4Change}/>
                      </div>
                      <div className="form-group">
                            <label>Answer</label>
                            <input type="checkbox" data-qno={i} className="form-control" value={1} onClick={this.handleAChange}/>1
                            <input type="checkbox" data-qno={i} className="form-control" value={2} onClick={this.handleAChange}/>2
                            <input type="checkbox" data-qno={i} className="form-control" value={3} onClick={this.handleAChange}/>3
                            <input type="checkbox" data-qno={i} className="form-control" value={4} onClick={this.handleAChange}/>4
                            
                      </div>
                  </div>)
              },this)}            

                <button type="submit" className="btn btn-default">Submit</button>
          </form>
        </div>


      </div>
    );
  }
}

export default CreateQuiz;