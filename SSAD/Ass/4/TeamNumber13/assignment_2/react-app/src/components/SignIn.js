import React, { Component } from 'react';
import './SignIn.css'
import Redirect from 'react-router-dom/Redirect';

class SignIn extends Component {
    constructor() {
        super();
        this.state = {
          formData: {
            username: "",
            password: "",
          },
          submitted: false,
    
        }
        this.handlePChange=this.handlePChange.bind(this)
        this.handleUChange=this.handleUChange.bind(this)
        this.handleSubmit=this.handleSubmit.bind(this)
        
      }

handlePChange(event){
    this.state.formData.password = event.target.value
}
handleUChange(event){
    this.state.formData.username = event.target.value
}

async handleSubmit(event){
    event.preventDefault()
    console.log("momo")
    console.log(this.state.formData)
    const request = new Request('http://localhost:8080/user',{
     method: 'POST',
     body: JSON.stringify(this.state.formData),
   })
      
   const response = await fetch(request)
   var data = await response.json()
   if(response.status==200){
      localStorage.setItem("LoggedIn",JSON.stringify(true))
      localStorage.setItem("userlogged",this.state.formData.username)
   }
   alert(data.message)
   this.setState({submitted:true})
   window.location.reload()
   
}

  render() {
    if(localStorage.getItem("LoggedIn")==="true"){
      return(<Redirect to="/" />)
    }


    return (
      <div className="App">
        <header className="App-header">
          <h1 className="App-title">Sign In</h1>
        </header>
        <div className="formContainer">
          <form onSubmit={this.handleSubmit}>
            <div className="form-group">
                <label>Username</label>
                <input type="text" className="form-control" value={this.state.genre} onChange={this.handleUChange}/>
            </div>
            <div className="form-group">
                <label>Password</label>
                <input type="password" className="form-control" value={this.state.genre} onChange={this.handlePChange}/>
            </div>           

                <button type="submit" className="btn btn-default">Login</button>
          </form>
        </div>



      </div>
    );
  }
}

export default SignIn;