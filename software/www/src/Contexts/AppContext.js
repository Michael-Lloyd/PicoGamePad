import { createContext } from 'react';

export const defaultAppData = {
	buttonLabels: 'PicoGamePad-v3A',
};

export const AppContext = createContext(defaultAppData);
