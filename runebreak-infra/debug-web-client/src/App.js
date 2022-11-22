import RegisterForm from './RegisterForm'
import logo from './logo.svg';
import './App.css';
import React, {Text, useEffect, useState} from 'react';
import doRegister from './doRegister';

function App() {
   const onSubmit = (username, password) => {
    console.log(`onSubmit called: ${username} -- ${password}`);
    doRegister(username, password);
   };

  return (
    <div className="App">
      <RegisterForm onSubmit={onSubmit} usernameLabel={'Username'} passwordLabel={'Password'}/>
    </div>
  );
}

export default App;