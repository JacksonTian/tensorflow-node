'use strict';

const tf = require('bindings')('binding.node');
// const ops = require('./lib/ops');

tf.placeholder = function (graph, status, name = 'feed') {
  const desc = new tf.Operation(graph, 'Placeholder', name);
  desc.setAttrType('dtype', tf.DataType.INT32);
  return tf.finishOperation(desc, status);
};

module.exports = tf;
