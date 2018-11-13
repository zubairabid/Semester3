import React, { Component } from 'react';
import Redirect from 'react-router-dom/Redirect';

class Quiz extends Component {
    constructor() {
        super();
        this.state = {
        
            id : localStorage.getItem('quiz_id'),
            myquiz: {quests:[],},
            submitted: false,
            mounted: false,
            correct: 0,
            formData: {},
        }
        this.handleAChange = this.handleAChange.bind(this)
        this.handleSubmit = this.handleSubmit.bind(this)
        
}

componentDidMount() {
    this.state.mounted=true
    const request = new Request('http://127.0.0.1:8080/quizzes/'+this.state.id,{
        method: 'GET'
    });
    fetch(request)
      .then(response => response.json())
        .then(data => this.setState({myquiz: data}));
  }

  handleAChange(event){
    this.state.myquiz.quests[event.target.getAttribute('data-qno')-1].attempted[event.target.value-1] = !(this.state.myquiz.quests[event.target.getAttribute('data-qno')-1].attempted[event.target.value-1])
  }

  handleSubmit(event){
    event.preventDefault()
    for (let i = 0; i < this.state.myquiz.quests.length; i++) {
      if( JSON.stringify(this.state.myquiz.quests[i].ans)===JSON.stringify(this.state.myquiz.quests[i].attempted)){
        this.state.correct++;
      }
    }
      this.state.formData.username = localStorage.getItem('userlogged')
      this.state.formData.correct =  this.state.correct
      this.state.formData.genre = this.state.myquiz.genre
      this.state.formData.quiz_id = this.state.myquiz.id
      var sent_json
      sent_json = this.state.formData
      console.log(sent_json)

      fetch('http://localhost:8080/quizans', {
        method: 'POST',
        body: JSON.stringify(sent_json),
      })
         .then(response => {
           if(response.status >= 200 && response.status < 300){
             alert("You got "+this.state.correct+" right answers")
             window.location = "http://localhost:3000/Quizzes"
           }
         });

      
    }

  render() {

    if(localStorage.getItem("LoggedIn")==="false"){
      return(<Redirect to="/" />)
    }

      for(let i=0;i<this.state.myquiz.quests.length;i++){
        this.state.myquiz.quests[i].opt = JSON.parse(this.state.myquiz.quests[i].options)
        this.state.myquiz.quests[i].ans = JSON.parse(this.state.myquiz.quests[i].answer)
        this.state.myquiz.quests[i].attempted = [false,false,false,false]
      }
    return (
      <div className="App">
        <header className="App-header">
          <h1 className="App-title">Quiz</h1>
        </header>
        <ol>
        {this.state.myquiz.quests.map(function(item,key){
          return(
            <li>
                <h5 className="App-title">{item.statement}</h5>
                <input type="checkbox" data-qno={key+1} className="form-control" value={1} onClick={this.handleAChange}/>{item.opt[0]}<br/>
                <input type="checkbox" data-qno={key+1} className="form-control" value={2} onClick={this.handleAChange}/>{item.opt[1]}<br/>
                <input type="checkbox" data-qno={key+1} className="form-control" value={3} onClick={this.handleAChange}/>{item.opt[2]}<br/>
                <input type="checkbox" data-qno={key+1} className="form-control" value={4} onClick={this.handleAChange}/>{item.opt[3]}<br/>
                </li>
          )

        },this)
      }
        </ol>
        <button onClick={this.handleSubmit}>Submit</button>

      </div>
    );
  
    }
}

export default Quiz;