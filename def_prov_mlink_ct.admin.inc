<?php

function def_prov_mlink_ct_admin_settings() {
  
  $ct_list = node_type_get_types();

  $conf = def_prov_mlink_ct_get_config();

  $form['from'] = array(
    '#type'=> 'item',
    '#title' => t('Provide a menu link'),
    '#markup' => t('For each content type, select if "Provide a menu link" should be enabled by default on node add pages.')
  );

  foreach ($ct_list as $ct_machine_name => $obj) {

    $def = isset($conf[$ct_machine_name]) ? $conf[$ct_machine_name] : 0;

    $form['enable_'.$ct_machine_name] = array(
      '#type' => 'checkbox',
      '#title' => $obj->name,
      '#default_value' => $def
    );
  }

  $form['#submit'][] = 'def_prov_mlink_ct_admin_settings_submit';
  return system_settings_form($form, TRUE);
}

function def_prov_mlink_ct_admin_settings_submit($form, $form_state) {

  $config = array();

  $ct_list = node_type_get_types();

  foreach ($ct_list as $ct_machine_name => $obj) {
    $data = array(
      'content_type' => $ct_machine_name,
      'enabled' => $form_state['values']['enable_'.$ct_machine_name],
    );
    $config[] = $data;
  }

  def_prov_mlink_ct_save_config($config);
}

?>
