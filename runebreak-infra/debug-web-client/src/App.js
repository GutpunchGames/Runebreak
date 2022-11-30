import RegisterForm from './RegisterForm'
import './App.css';
import React from 'react';
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