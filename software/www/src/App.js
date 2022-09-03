/*
 *  Author:     Michael Lloyd (micl.dev)
 *  Version:    1.0.0
 *  Date:       18/10/22
 *
 *      __   ___.--'_`. 
 *     ( _`.'. -   'o` ) 
 *     _\.'_'      _.-'  
 *     ( `. )    //`    
 *     \_`-'`---'\__,   
 *      \`        \\`--    
 *
 */

/*
 *	Dependencies & Imports
 */
import React, { useState } from 'react';
import { BrowserRouter as Router, Route, Switch } from "react-router-dom";

/*
 *	Components
 *	Desc: React pages, components and data files.
 */
import { AppContext } from './Contexts/AppContext';
import Navigation from './Components/Navigation'
import HomePage from './Pages/HomePage'
import PinMappingPage from "./Pages/PinMapping";
import ResetSettingsPage from './Pages/ResetSettingsPage';
import SettingsPage from './Pages/SettingsPage';
import DisplayConfigPage from './Pages/DisplayConfig';
import LEDConfigPage from './Pages/LEDConfigPage';
import { loadButtonLabels } from './Services/Storage';

/*
 *	Styling
 *	Desc: Stylesheet and style applicators 
 */
import './Styles/App.scss';

/*
 *	Application Body
 */
const App = () => {
	const [buttonLabels, setButtonLabels] = useState(loadButtonLabels() ?? 'PicoGamePad-v3A');

	const appData = {
		buttonLabels,
		setButtonLabels,
	};

	return (
		<AppContext.Provider value={appData}>
			<Router>
				<Navigation />
				<div className="container-fluid body-content">
					<Switch>
						<Route exact path="/">
							<HomePage />
						</Route>
						<Route path="/settings">
							<SettingsPage />
						</Route>
						<Route path="/pin-mapping">
							<PinMappingPage />
						</Route>
						<Route path="/reset-settings">
							<ResetSettingsPage />
						</Route>
						<Route path="/led-config">
							<LEDConfigPage />
						</Route>
					</Switch>
				</div>
			</Router>
		</AppContext.Provider>
	);
}

/*
 *	Exports
 */
export default App;
