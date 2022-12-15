import LoginForm from './LoginForm'
import RegisterForm from './RegisterForm'
import './App.css';
import React from 'react';
import doRegister from './doRegister';
import doLogin from './doLogin';
import PatchUserForm from './PatchUserForm';
import doUpdateUser from './doUpdateUser';

function App() {

  const onSubmitRegister = (username, password) => {
    doRegister(username, password);
  };

  const onSubmitLogin = (username, password) => {
    doLogin(username, password);
  };

  const onSubmitUpdateUser = (username, userId, token) => {
    doUpdateUser(username, userId, token);
  };

  return (
    <div className="App">
      <RegisterForm onSubmit={onSubmitRegister} usernameLabel={'Username'} passwordLabel={'Password'}/>
      <LoginForm onSubmit={onSubmitLogin} usernameLabel={'Username'} passwordLabel={'Password'}/>
      <PatchUserForm onSubmit={onSubmitUpdateUser} usernameLabel={'Username'} userIdLabel={'User ID'} tokenLabel={'Token'}/>
    </div>
  );
}

export default App;