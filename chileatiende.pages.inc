<?php



/**
 * 
 */
function chileatiende_page_main() {
	$items = array(
    l('Fichas','chileatiende/fichas'),
    l('Servicios','chileatiende/servicios')
  );
  return theme('item_list',array('items' => $items));
}



/**
 * 
 */
function chileatiende_search_servicio_form($form, $form_state, $servicio_id) {
  $form['servicio_id'] = array(
    '#type' => 'textfield',
    '#title' => 'Servicio',
    '#default_value' => $servicio_id,
    '#description' => 'Ingrese el ID del servicio',
    '#size' => 10,
    '#element_validate' => array('chileatiende_search_validate_id')
  );
  
  $form['search'] = array(
    '#type' => 'submit',
    '#value' => t('Search')
  );
  return $form;
}



/**
 * 
 */
function chileatiende_search_servicio_form_submit($form, &$form_state) {
  $redirect = 'chileatiende/servicios/' . $form_state['values']['servicio_id'];
  $form_state['redirect'] = $redirect;
}



/**
 * 
 */
function chileatiende_search_validate_id($element, &$form_state, $form) {
  $form_state['values'][$element['#name']] = trim($form_state['values'][$element['#name']]);

}




/**
 * 
 */
function chileatiende_search_ficha_form($form, $form_state, $ficha_id) {
  $form['ficha_id'] = array(
    '#type' => 'textfield',
    '#title' => 'Ficha',
    '#default_value' => $ficha_id,
    '#description' => 'Ingrese el ID de la ficha',
    '#size' => 10,
    '#element_validate' => array('chileatiende_search_validate_id')
  );
  
  $form['search'] = array(
    '#type' => 'submit',
    '#value' => t('Search')
  );
  return $form;
}



/**
 * 
 */
function chileatiende_search_ficha_form_submit($form, &$form_state) {
  $redirect = 'chileatiende/fichas/' . $form_state['values']['ficha_id'];
  $form_state['redirect'] = $redirect;
}






/**
 * 
 */
function chileatiende_ficha_page($ficha_id, $filters = array()) {
  $form_ficha = drupal_get_form('chileatiende_search_ficha_form', $ficha_id);
  $output = drupal_render($form_ficha);
  $output .= chileatiende_output('ficha',$ficha_id);
  
  return $output;
  
  
  
}



/**
 * 
 */
function chileatiende_servicio_page($servicio_id, $filter = array()) {
  $form_servicio = drupal_get_form('chileatiende_search_servicio_form', $servicio_id);
  $output = drupal_render($form_servicio);

  $output .= chileatiende_output('servicio', $servicio_id);
  $fichas = chileatiende_get_fichas_by_servicio($servicio_id);
  if(isset($fichas['fichas']['items'])) {
    $output .= '<h2>Fichas del Servicio</h2>';
    $rows = array();
    foreach($fichas['fichas']['items'] as $ficha) {
      $rows[] = array(
        l($ficha['codigo'],'chileatiende/fichas/' . $ficha['codigo']),
        $ficha['titulo'],

      );
    }
    $output .= theme('table',array('rows' => $rows));
  }
  return $output;
}
 
 


/**
 * 
 */
function chileatiende_fichas_page() {
  $output  = '';
  $next = null;
	if(isset($_GET['next']) && $_GET['next'] != '') {
		$next = $_GET['next'];
	}
	$data = chileatiende_get_list('fichas', $next);
	if(is_array($data)) {
		$rows = array();
	
		foreach($data['fichas']['items']['ficha'] as $ficha) {
			$rows[] = array(
				l($ficha['codigo'],'chileatiende/fichas/' . $ficha['codigo']),
				$ficha['servicio'],
	      $ficha['titulo'],
				$ficha['permalink']
			);
		}
		
		$vars = array(
			'rows' => $rows,
			'header' => array('Código','Servicio','Título','Permalink')
		);
		$output .= theme('table',$vars);
		if($data['fichas']['nextPageToken']) {
			$query = array(
				'next' => $data['fichas']['nextPageToken'],
				'prev' => isset($_GET['next'])?$_GET['next']:'',
			);
			if(isset($_GET['prev'])) {
				$query_prev = array(
					'next' => $_GET['prev'],
				);
				$output .= l(t('Anterior'),'chileatiende/fichas', array('query' => $query_prev));
				
			}
			$output .= l(t('Siguiente'),'chileatiende/fichas', array('query' => $query));
		}
		return $output;
	}
	return '';
	

}



/**
 * 
 */
function chileatiende_servicios_page() {
  $output  = '';

	$data = chileatiende_get_list('servicios');

	$rows = array();
	
	foreach($data['servicios']['items']['servicio'] as $servicio) {
		$rows[] = array(
			l($servicio['id'],'chileatiende/servicios/' . $servicio['id']),
			$servicio['nombre'],
      $servicio['url'],
      $servicio['mision']
		);
	}
	
	$vars = array(
		'rows' => $rows,
		'header' => array('Código','Servicio','Url','Misión')
	);
	$output .= theme('table',$vars);
	
	return $output;
}