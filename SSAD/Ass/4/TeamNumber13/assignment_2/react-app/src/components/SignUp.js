import React, { Component } from 'react';
import './SignUp.css'
import Redirect from 'react-router-dom/Redirect';

class SignUp extends Component {
    constructor() {
        super();
        this.state = {
          formData: {
            name: "",
            username: "",
            password: "",
          },
          submitted: false,
    
        }
        this.handleFChange=this.handleFChange.bind(this)
        this.handlePChange=this.handlePChange.bind(this)
        this.handleUChange=this.handleUChange.bind(this)
        this.handleSubmit=this.handleSubmit.bind(this)
        
      }
handleFChange(event){
    this.state.formData.name = event.target.value
}

handlePChange(event){
    this.state.formData.password = event.target.value
}
handleUChange(event){
    this.state.formData.username = event.target.value
}

async handleSubmit(event){
    event.preventDefault();
    
    console.log(this.state.formData)
    const request = new Request('http://localhost:8080/newuser',{
     method: 'POST',
     body: JSON.stringify(this.state.formData),
   })
      
   const response = await fetch(request)
   var data = await response.json()
   console.log(data)
   alert(data.message)
}

  render() {
    if(localStorage.getItem("LoggedIn")==="true"){
      return(<Redirect to="/" />)
    }
    return (
      <div className="App">
        <header className="App-header">
          <h1 className="App-title">Sign Up</h1>
        </header>
        <div className="formContainer">
          <form onSubmit={this.handleSubmit}>
            <div className="form-group">
                <label>Full Name</label>
                <input type="text" className="form-control" value={this.state.genre} onChange={this.handleFChange}/>
            </div>
            <div className="form-group">
                <label>Username</label>
                <input type="text" className="form-control" value={this.state.genre} onChange={this.handleUChange}/>
            </div>
            <div className="form-group">
                <label>Password</label>
                <input type="password" className="form-control" value={this.state.genre} onChange={this.handlePChange}/>
            </div>           

                <button type="submit" className="btn btn-default">Submit</button>
          </form>
        </div>



      </div>
    );
  }
}

export default SignUp;