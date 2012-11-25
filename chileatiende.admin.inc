<?php



/**
 * 
 */
function chileatiende_settings_form($form, $form_state) {
	$form['chileatiende_access_token'] = array(
		'#type' => 'textfield',
		'#required' => TRUE,
		'#title' => 'Access Token',
		'#default_value' => variable_get('chileatiende_access_token',''),
		'#description' => t('Token para acceder al servicio de ChileAtiende')
	);
	$form['chileatiende_watchdog'] = array(
    '#type' => 'checkbox',
    '#title' => 'Activar Watchdog',
    '#default_value' => variable_get('chileatiende_watchdog',0),
    '#description' => 'Si esta activado, se registrará en el log de drupal cada vez que se conecta a ChileAtiende',
  );
	
	return system_settings_form($form);
}
