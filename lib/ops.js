// 'use strict';

// class DefaultStack {
//   // """A thread-local stack of objects for providing implicit defaults."""

//   constructor() {
//     this._enforce_nesting = true;
//     this.stack = [];
//   }

//   getDefault() {
//     if (this.stack.length >= 1) {
//       return this.stack[this.stack.length - 1];
//     }
//     return null;
//   }

//   reset() {
//     this.stack = [];
//   }

//   get enforce_nesting() {
//     return this._enforce_nesting;
//   }

//   set enforce_nesting(value) {
//     this._enforce_nesting = value;
//   }

//   * get_controller(_default) {
//     // """A context manager for manipulating a default stack."""
//     try {
//       this.stack.append(_default);
//       yield _default;
//     } finally {
//       if (this._enforce_nesting) {
//         if (this.stack[this.stack.length - 1] !== _default) {
//           throw new TypeError(
//               `Nesting violated for default stack of ${typeof _default} objects`);
//         }

//         this.stack.pop();
//       } else {
//         // TODO
//         this.stack.remove(_default);
//       }
//     }
//   }
// }

// const _default_session_stack = new DefaultStack();

// class DefaultGraphStack extends DefaultStack {

//   /// """A thread-local stack of objects for providing an implicit default graph."""

//   constructor() {
//     super();
//     this._global_default_graph = null;
//   }

//   getDefault() {
//     /// """Override that returns a global default if the stack is empty."""
//     return super.getDefault() || this.getGlobalDefaultGraph();
//   }

//   getGlobalDefaultGraph() {
//     if (!this._global_default_graph) {
//       this._global_default_graph = new Graph();
//     }

//     return this._global_default_graph;
//   }

//   reset() {
//     super.reset();
//     this._global_default_graph = null;
//   }
// }

// const _default_graph_stack = new DefaultGraphStack();

// exports.getDefaultGraph = function () {
//   return _default_graph_stack.getDefault();
// };
