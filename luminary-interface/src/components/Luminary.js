import React from 'react';
import Particle from 'particle-api-js';

export default class extends React.Component {

    constructor(props) {
        super(props);
        this.state = {
            _settings: props.settings,
            _particle: new Particle()
        };
    };

    componentDidMount() {
        this.state._particle.login({
            username: this.state._settings.username, 
            password: this.state._settings.password
        })
        .then( data => {
            console.log(data.body.access_token); //DEV
            this.setState({token: data.body.access_token});
        })
        .catch( err => {
            console.log('Could not log in.', err);
        });

        fetch("https://api.particle.io/v1/devices", { 
            method: "GET", 
            access_token: this.state._settings.access_token
        }).then(res => {
            if (res.status === 400) {
                console.log("error", res.body)
                return
            }
            return res.body
        })
    }

    deviceInfo = () => {
        
    }

    render() {
        return (
            <div id="luminary">
                <header className="App-header">
                    <h1>Luminary</h1>
                </header>
                <div id="timezone">
                    <h2>Time zone</h2>
                    <input id="timezone"/> {}
                </div>
                <div>
                    <h2>Clock Hands</h2>
                    <p>Hour <input/></p>
                    <p>Minute <input/></p>
                    <p>Second <input/></p>
                </div>
            </div>
    );}
};