'use strict';

const tf = require('./');

const a = tf.constant([1.0, 2.0], 'a');
const b = tf.constant([2.0, 3.0], 'b');

const result = tf.add(a, b, 'add');

console.log(result);
