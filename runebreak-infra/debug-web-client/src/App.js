import LoginForm from './LoginForm'
import RegisterForm from './RegisterForm'
import './App.css';
import React from 'react';
import doRegister from './doRegister';
import doLogin from './doLogin';

function App() {
   const onSubmitRegister = (username, password) => {
    doRegister(username, password);
   };

   const onSubmitLogin = (username, password) => {
    doLogin(username, password);
   };

  return (
    <div className="App">
      <RegisterForm onSubmit={onSubmitRegister} usernameLabel={'Username'} passwordLabel={'Password'}/>
      <LoginForm onSubmit={onSubmitLogin} usernameLabel={'Username'} passwordLabel={'Password'}/>
    </div>
  );
}

export default App;