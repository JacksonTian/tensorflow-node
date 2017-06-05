'use strict';

const tf = require('./');

const hello = tf.constant('Hello, TensorFlow!')
const sess = tf.Session();

sess.run(hello);
