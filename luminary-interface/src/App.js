
import React from 'react';
import './App.css';
import Luminary from './components/Luminary';

import * as appConfig from './appConfig.json';


export default App => {
  return (
    <div id="App" className="App">
      <Luminary settings={appConfig.particle}/>
    </div>
  );
};