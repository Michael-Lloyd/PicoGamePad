import React, { useEffect, useState } from 'react';
import axios from 'axios';
import { orderBy } from 'lodash';

import Section from '../Components/Section';

const currentVersion = process.env.REACT_APP_CURRENT_VERSION;
const latestVersion = 'VALUE INDEV';

export default function HomePage() {

	return (
		<div>
			<h1>PicoGamePad v3A Configuration Interface API (indev)</h1>
			<p>Please select a menu option to proceed.</p>
			<Section title="Firmware Version">
				<div className="card-body">
					<div className="card-text">Current Version: { currentVersion }</div>
					<div className="card-text">Latest Version: { latestVersion }</div>
				</div>
			</Section>
		</div>
	);
}
