import logo from './logo.svg';
import './App.css';
import {Text, useEffect, useState} from 'react';

function App() {
  const [posts, setPosts] = useState([]);
     useEffect(() => {
      fetch('http://localhost:9001/')
      .then((data) => data.json())
         .then((data) => {
            console.log(data);
            setPosts(data);
         })
         .catch((err) => {
            console.log(err.message);
         });
   }, []);

  const smth = 'something';

  return (
    <div className="App">
      <header className="App-header">
        <img src={logo} className="App-logo" alt="logo" />
        <p>
          Edit <code>src/App.js</code> and save to reload.
        </p>
        <a
          className="App-link"
          href="https://reactjs.org"
          target="_blank"
          rel="noopener noreferrer"
        >
          Learn React
          <p>
          ({posts && `Got response from server: ${posts.Name}`})
          </p>
        </a>
      </header>
    </div>
  );
}

export default App;
