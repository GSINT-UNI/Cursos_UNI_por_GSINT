import React from 'react';
import Menu from './menu/Menu'



//import { userService } from '../_services';

class HomePage extends React.Component {
    
    constructor(props) {
        super(props);

        this.state = {
            user: {},
            users: []
        };
    }

    componentDidMount() {
        this.setState({ 
            user: JSON.parse(localStorage.getItem('user')),
            users: { loading: true }
        });
      //  userService.getAll().then(users => this.setState({ users }));
    }

    render() {
      
      //  const { user, users } = this.state;
        return (
            <div>
                <div> <Menu /> </div>
            </div>
        );
    }
}

export { HomePage };